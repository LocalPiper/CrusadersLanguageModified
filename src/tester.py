import subprocess
import os
import difflib
import sys

TEST_DIR = "tests"
OUTPUT_DIR = "tests/outputs"
EXECUTABLE = "bin/clm"

def run_program(input_path):
    try:
        result = subprocess.run(
            [EXECUTABLE],
            stdin=open(input_path, "r"),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            timeout=5
        )
    except subprocess.TimeoutExpired:
        return False, "Execution timed out", ""
    except FileNotFoundError:
        return False, f"Executable not found: {EXECUTABLE}", ""
    
    if result.returncode != 0:
        return False, f"Non-zero exit code {result.returncode}:\n{result.stderr}", result.stdout

    return True, "", result.stdout

def main():
    write_mode = "--write" in sys.argv
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    tests = [f for f in os.listdir(TEST_DIR) if f.endswith(".cl2")]
    total = len(tests)
    passed = 0
    written = 0

    for test_file in sorted(tests):
        input_path = os.path.join(TEST_DIR, test_file)
        expected_output_path = os.path.join(OUTPUT_DIR, test_file.replace(".cl2", ".out"))

        success, error_msg, actual_output = run_program(input_path)

        if not success:
            print(f"[ERROR] {test_file}\n{error_msg}")
            continue

        if write_mode:
            with open(expected_output_path, "w") as f:
                f.write(actual_output)
            print(f"[WROTE] {expected_output_path}")
            written += 1
            continue

        if not os.path.exists(expected_output_path):
            print(f"[MISSING] {expected_output_path} (use --write to generate)")
            continue

        with open(expected_output_path, "r") as f:
            expected_output = f.read()

        if actual_output != expected_output:
            diff = list(difflib.unified_diff(
                expected_output.splitlines(keepends=True),
                actual_output.splitlines(keepends=True),
                fromfile='expected',
                tofile='actual'
            ))
            print(f"[FAIL] {test_file}")
            print("".join(diff[:10])) 
        else:
            print(f"[PASS] {test_file}")
            passed += 1

    if write_mode:
        print(f"\nWrote expected outputs for {written} test(s).")
    else:
        print(f"\nSummary: {passed}/{total} tests passed.")

if __name__ == "__main__":
    main()

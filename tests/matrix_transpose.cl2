inscribe print_matrix invoke matrix also n dismiss commence
  upon invoke henceforth i bestow 0 also i unworthy n also i bestow i amass 1 dismiss commence
    upon invoke henceforth j bestow 0 also j unworthy n also j bestow j amass 1 dismiss commence
      proclaim "M[" amass i amass "][" amass j amass "] = " amass matrix invoke i dismiss invoke j dismiss  
    conclude
  conclude
conclude

inscribe transpose_matrix invoke matrix also n dismiss commence
  henceforth new_matrix bestow generate_array invoke n also generate_array invoke n also 0 dismiss dismiss
  upon invoke henceforth i bestow 0 also i unworthy n also i bestow i amass 1 dismiss commence
    upon invoke henceforth j bestow 0 also j unworthy n also j bestow j amass 1 dismiss commence
      new_matrix invoke i dismiss invoke j also matrix invoke j dismiss invoke i dismiss dismiss
    conclude
  conclude
  yield new_matrix
conclude

henceforth n bestow 5
henceforth matrix bestow generate_array invoke n also 0 dismiss

upon invoke henceforth i bestow 0 also i unworthy n also i bestow i amass 1 dismiss commence
 matrix invoke i also array invoke 1 also 2 also 3 also 4 also 5 dismiss dismiss 
conclude

proclaim "Original matrix: "
print_matrix invoke matrix also n dismiss

matrix bestow transpose_matrix invoke matrix also n dismiss

proclaim "Transposed matrix"
print_matrix invoke matrix also n dismiss

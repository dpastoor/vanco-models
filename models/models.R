library(overseer)

# check to make sure sourcing from proper directory if running interactively
if (!interactive_model_check("frymoyer_2014.cpp")) {
    stop("make sure the directory is set to the models directory before running interactively,
    to make sure the relative paths will be the same as when sourcing")
}

models <- Overseer$new()

models$add_model_file("frymoyer_2014.cpp")
models$add_model_file("lo_2010.cpp")
models$add_model_file("anderson_2007.cpp")
models$add_model_file("capparelli_2013.cpp")
models$add_model_file("stockmann_2015.cpp")


# add model files below


# return overseer instance to be pulled in via source()$value
# do not add any code below this line or delete the models object
# or sourcing the file may not work properly
models


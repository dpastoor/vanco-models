library(overseer)

# check to make sure sourcing from proper directory if running interactively
if (!interactive_model_check("<REPLACEWITHYOURFIRSTMODEL.cpp>")) {
    stop("make sure the directory is set to the models directory before running interactively,
    to make sure the relative paths will be the same as when sourcing")
}

models <- Overseer$new()


# add model files below


# return overseer instance to be pulled in via source()$value
# do not add any code below this line or delete the models object
# or sourcing the file may not work properly
models


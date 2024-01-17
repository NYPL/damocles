#!/usr/local/bin/Rscript --vanilla

library(scriptName)

dyn.load("bin/dlog-r.so")

dlog <- function(module, log_message) {
  print(current_filename())
  print(current_source_filename())
  .C("dlog_for_R", module=module, log_message=log_message)
}

# Lout
A lightweight logging framework

**Work in progress**

## Features
* Customizable log-levels
  * Active levels can be adjusted at run-time.
* Support for custom output channels (simply inherit from `output::IOutput`)
* Filtering - log messages can be categorized with a custom string which enables filtering on that category.
  * Priority categories - if a message is tagged with a priority category, it will be logged regardless of active level.
* Operator overloading for short-hand logging.


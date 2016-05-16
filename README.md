# lout
A lightweight logging framework

****Work in progress****

## Design goals
* No predefined log-levels (translation to human readable text via interface provided by user)
* Pluggable, i.e. able to log to several different channels (std::err, file, stream etc.)
* Thread-safe
* Low memory footprint

## Notes
* Log rotation etc. are the responsibility of output printers, if applicable.
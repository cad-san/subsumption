#Subsumption

 [![Build Status](https://travis-ci.org/cad-san/subsumption.png?branch=master)](https://travis-ci.org/cad-san/subsumption)
 [![Coverage Status](https://coveralls.io/repos/cad-san/subsumption/badge.png)](https://coveralls.io/r/cad-san/subsumption)

##Overview
This is simple library to implements "subsumption architecture" devised by Rodney Allen Brooks.

This library doesn't implement actuators and sencers, but we provide the interfaces for sencing the environment and behavior as reactions. 

So you can make the concrete implements wheather physical robot or simulator.

##Getting Started

You'll need to the following to get stared:

* install boost library(with boost::thread)
* download latest version

```
 $ git clone git://github.com/cad-san/subsumption.git
```

* download cpputest

```
 $ git submodule init
 $ git submodule update
```

* make library

```
 $ make
```

----

**BUT**, I'm sorry that this libray is in the process of production (x_x)

Now there is **ONLY** test cord to develop this library.
Samples for using library will be made soon.

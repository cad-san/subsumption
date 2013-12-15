#Subsumption

 [![Build Status](https://travis-ci.org/cad-san/subsumption.png?branch=master)](https://travis-ci.org/cad-san/subsumption)
 [![Coverage Status](https://coveralls.io/repos/cad-san/subsumption/badge.png)](https://coveralls.io/r/cad-san/subsumption)

##Overview
This is simple library to implements "subsumption architecture" devised by Rodney Allen Brooks.

This library doesn't implement actuators and sencers, but we provide the interfaces for sencing the environment and behavior as reactions. 

So you can make the concrete implements wheather physical robot or simulator.

##Getting Started

You'll need to the following to get stared:

* install boost library(with boost::thread, boost::system)
* download latest version

```
 $ git clone git://github.com/cad-san/subsumption.git
```

* make library

```
 $ make
```

## How to use

I'm sorry that now there is **ONLY** test cord to develop this library (x_x)

Samples for using library will be made soon.

----

## Test this library

If you want to test this library, you'll need to the following procedure.

* download cpputest

```
 $ git submodule init
 $ git submodule update
```

* command make test

```
 $ make test
```

## License

[The MIT License (MIT)](http://opensource.org/licenses/mit-license.php)

Copyright (c) 2013 cad-san

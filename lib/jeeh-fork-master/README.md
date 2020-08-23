# Changes

Changes from the [original repo](https://git.jeelabs.org/jcw/jeeh/commits/branch/master):

* Add ADC functionality to the STM32F4 architecture, along with functions that read `vref` and the temperature
* Move STM32F4 `enableClkAt168MHz()` and `fullSpeedClock()` functions to a `.cpp` file

# JeeH

Headers for framework- and platform-agnostic code.

* This code can be used in combination with arduino, libopencm3, mbed, and
  other frameworks.
* A good C++ compiler with C++11 support is essential, due to heavy use of C++
  templates.
* The resulting code is small (_really small_, sometimes) and fast (_really
  fast_, sometimes).
* Everything here is in flux. API's will change, as better idioms are being
  discovered.
* This library is intended for use with
  [PlatformIO](https://platformio.org/lib/show/3082/JeeH): just add `JeeH` to
  `lib_deps`.

### Examples

See the
[Sampler](https://git.jeelabs.org/jcw/jeeh/src/branch/master/examples/sampler)
project.

### License

JeeH wants to stand on the shoulders of giants. Since all giants tend to prefer
their own licensing schemes (that's the perk of being a giant), JeeH bows in
total worship of each of them and lives in the public domain. Do as you wish.

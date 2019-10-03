<img src="https://proxy.duckduckgo.com/iu/?u=https%3A%2F%2Ftse1.mm.bing.net%2Fth%3Fid%3DOIP.UpYpMIfsXsORJXAR4do7KgAAAA%26pid%3DApi&f=1" alt="Book Cover" height="62px" width="42px" align="left"><br><br>

# Design Patterns in Modern C++
<div>
    <a href="https://github.com/NaPiZip/Tipps-and-tricks">
        <img src="https://img.shields.io/badge/Document%20Version-0.0.1-green.svg"/>
    </a>
    <a href="https://www.microsoft.com">
        <img src="https://img.shields.io/badge/Windows%2010%20x64-10.0.17134%20Build%2017134-blue.svg"/>
    </a>
    <a href="https://cmake.org/">
        <img src="https://img.shields.io/badge/CMake-3.15.3-blue"/>
    </a>
    <a href="https://visualstudio.microsoft.com/vs/">
        <img src="https://img.shields.io/badge/Microsoft%20Visual%20Studio-16.3.1-blue"/>
    </a>
</div>

## Introduction
This repository contains my notes and source files of the book `Design Patterns in Modern C++` by Dmitri Nesteruk. I created this repository in order to have a centralized space for my code. My notes are not complete by any means, they only consist of content which I thought is helpful.

## Tipps
<b>How to add `cpplint` to Visual Studio</b>
1. Install the [tool](https://github.com/google/styleguide):
```
$ python -m pip install cpplint
```
2. Add external tools to Visual Studio:
  ```
  Tools - External tools - Add - Title：cpplint
  command：cpplint -–output=vs7 $(ItemPath)
  Initial Directory：$(ItemDir)
  Use Output Window: checked
  ```
3. Add shortcut:
  ```
  Tools - Options - Environment - Keyboard
  Show commands containing：external
  Tools.ExternalCommand1
  Press shortcut keys
  ```

## Chapter 1: Introduction
The introduction contains a lot of compressed knowledge which at some point get described in detail in section 9, hence I am not covering those elements, only if I think it makes sense. Nevertheless the SOLID Design Principles is interesting and Important.

### The SOLID Design Principles
SOLID is an acronym which stands for the following design principles (and their abbreviations):
- Single Responsibility Principle (SRP)
- Open-Closed Principle (OCP)
- Liskov Substitution Principle (LSP)
- Interface Segregation Principle (ISP)
- Dependency Inversion Principle (DIP)

## Contributing
To get started with contributing to my GitHub repository, please contact me [Slack](https://join.slack.com/t/napi-friends/shared_invite/enQtNDg3OTg5NDc1NzUxLWU1MWNhNmY3ZTVmY2FkMDM1ODg1MWNlMDIyYTk1OTg4OThhYzgyNDc3ZmE5NzM1ZTM2ZDQwZGI0ZjU2M2JlNDU).

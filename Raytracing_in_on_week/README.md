<img src="https://raw.githubusercontent.com/RayTracing/raytracing.github.io/master/images/RTOneWeekend-small.jpg" alt="RTOneWeekend-small.jpg" height="62px" width="42px" align="left"><br><br>

# Ray Tracing in One Weekend Book
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
This repository contains my notes and source files of the book `Ray Tracing in One Weekend ` by Peter Shirley. I created this repository in order to have a centralized space for my code. My notes are not complete by any means, they only consist of content which I thought is helpful, the resources can be found [here](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

I am not documenting the chapters of the book because I think it is pretty well written and everything is explained very nicely.

## Notes
The following picture shows an example of the ray tracer in action, it is pretty amazing how simple the code is and what it can do. I generated the image based on the final section of the book, whit small changes to the camera position and antialiasing.

<p align="center">
<img src="https://raw.githubusercontent.com/NaPiZip/Programming-basics-cpp/master/Raytracing_in_on_week/images/cover.JPG" height="50%" width="50%" align="center"/></p>


I also tried to test the `Celero` benchmarking tool, which can be fond [here](https://github.com/DigitalInBlue/Celero).
I did some benchmarks which show the behavior of increasing the resolution, since the `main` function has two for loops, it's clear that increasing the dimension by 2 is almost doubling the runtime (see `InnerLoopNx`). I also did a benchmark on the antialiasing in `main`, because I was wondering if I could make the code faster. Using a `for_each` loop and `std::accumulate` did increase the time by the factor two. Surprisingly a standard algorithm with `std::execution::par` is slightly slower than the regular `for_each`. This was more of a fun exercise.

<p align="center">
<img src="https://raw.githubusercontent.com/NaPiZip/Programming-basics-cpp/master/Raytracing_in_on_week/images/benchmark.JPG"/></p>

**Result:
Do not guess, benchmark it!**

## Contributing
To get started with contributing to my GitHub repository, please contact me [Slack](https://join.slack.com/t/napi-friends/shared_invite/enQtNDg3OTg5NDc1NzUxLWU1MWNhNmY3ZTVmY2FkMDM1ODg1MWNlMDIyYTk1OTg4OThhYzgyNDc3ZmE5NzM1ZTM2ZDQwZGI0ZjU2M2JlNDU).

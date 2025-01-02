<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->


<!-- PROJECT LOGO -->
<br />
<div align="center">
      <img width="400" src="https://upload.wikimedia.org/wikipedia/commons/e/e5/Nanoscience_High-Performance_Computing_Facility.jpg" alt="logo"/>
  <h1 align="center">Parallel computing</h1>
</div>
<br>

<!-- ABOUT THE PROJECT -->
## About The Project

This repository showcases two university projects designed to explore and demonstrate key concepts in parallel computing design and implementation. These projects delve into various aspects of distributed computing, from schema design to code implementation and in depth research. They provide practical experience in working with real-world scenarios and highlight the importance of efficient parallel coding.

### Project 1 - Parallel Image Convolution

**Project Description:**

This project implements a parallel algorithm for applying a convolution filter to an image using shared memory on a MIMD architecture.  It's designed for educational purposes to explore the principles of parallel computing and image processing.

The core of the project is the parallel implementation of the convolution algorithm. The input image is represented as a 2D matrix (N x N), and the filter is a smaller 2D matrix (M x M, where M < N and M is odd).  The convolution process involves sliding the filter across the image, performing element-wise multiplication between the filter and the underlying image patch, and summing the results to produce a single output pixel value.  This is repeated for every possible position of the filter on the image.

The project utilizes a shared memory paradigm, meaning that all processor cores have access to the same memory space containing the image and filter data.  This allows for efficient data sharing and coordination between the parallel threads. The output is a new image matrix of the same size as the input image, where each pixel represents the result of the convolution operation at that corresponding location.

**Key Features:**

* **Parallel Convolution:**  The convolution operation is parallelized to leverage multi-core processors, significantly speeding up the process, especially for large images and filters.
* **Shared Memory:**  Utilizes shared memory for efficient data access and communication between parallel threads.
* **MIMD Architecture:**  Designed for execution on a Multiple Instruction, Multiple Data (MIMD) architecture, the dominant type of parallel architecture in modern computing.

**Repository Contents:**

* **Source code:**  The code itself.
* **Tests:**  The project includes some example test cases.

### Project 2 - Utilizing GPUs for AI Model Processing Seminar

This repository contains materials for a seminar on the utilization of Graphics Processing Units (GPUs) for processing Artificial Intelligence (AI) models. The seminar explores the historical context, technical advancements, and future trends in this critical area of computing.

**Project Description:**

The seminar covers the following key aspects:

* **The 3D Revolution and the Rise of GPUs:**  Traces the evolution of GPUs from their origins in 3D graphics processing to their current role as the backbone of AI computation.  It highlights the transition from fixed-function hardware to programmable shaders and the increasing demand for real-time 3D graphics that drove GPU advancements.
* **NVIDIA and GPGPU:** Focuses on NVIDIA's contribution to the field of General-Purpose computing on Graphics Processing Units (GPGPU) and the introduction of CUDA, a parallel computing platform and programming model that simplified GPU programming.
* **GPUs in AI:** Explains the pivotal role of GPUs in accelerating AI research and development.  It highlights the significant performance gains observed in AI tasks when using GPUs compared to traditional CPUs and discusses the growth in model complexity, exemplified by models like GPT, and their increasing parameter counts.
* **Distributed Training:** Addresses the challenges of memory limitations and performance bottlenecks when training large AI models. Introduces the concept of distributed training using interconnected GPU clusters, often facilitated by cloud computing infrastructure.
* **NVLink:** Describes NVLink, a high-speed interconnect technology developed by NVIDIA to enable efficient communication between GPUs, improving performance in distributed training scenarios.
* **Parallelism Techniques:** Explains different parallelism strategies employed in distributed GPU training, such as data parallelism, model parallelism, and pipeline parallelism.
* **Tensor Cores:** Dives into the architecture and functionality of Tensor Cores, specialized hardware units within NVIDIA GPUs designed to accelerate matrix operations, particularly fused multiply-add (FMA) operations, which are fundamental to deep learning computations.
* **Comparison: CUDA Core vs. Tensor Core:**  Compares the performance of CUDA cores and Tensor Cores, demonstrating the significant speedup offered by Tensor Cores for matrix operations.
* **TPUs and NPUs:** Explores alternative hardware accelerators, including Google's Tensor Processing Units (TPUs) and Neural Processing Units (NPUs), highlighting their specialized architectures and applications.  It explains how TPUs excel in training and inference of neural networks, especially in large-scale data centers, while NPUs are optimized for low-power and high-efficiency inference at the edge, such as in mobile devices and autonomous vehicles.
* **AlexNet and its Impact:** Examines the historical significance of AlexNet, a convolutional neural network that demonstrated the power of GPUs in image recognition and spurred the widespread adoption of GPUs for deep learning. Discusses the technical details of AlexNet's implementation and its impact on AI research.
* **CNNs and Transformers:** Provides an overview of the benefits of GPU acceleration for Convolutional Neural Networks (CNNs) and Transformers, two dominant architectures in deep learning.  Explains how GPUs facilitate parallel processing of convolutions, pooling operations, and attention mechanisms.

  
### Built With

[![My Skills](https://skillicons.dev/icons?i=c)](https://skillicons.dev)


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/othneildrew/Best-README-Template/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/othneildrew/Best-README-Template/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/othneildrew/Best-README-Template/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/othneildrew
[product-screenshot]: images/screenshot.png
[Next.js]: https://img.shields.io/badge/next.js-000000?style=for-the-badge&logo=nextdotjs&logoColor=white
[Next-url]: https://nextjs.org/
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 

# VSSS Simulation Protobuf Messages

## 📜 Index <!-- omit in toc -->

- [🎉 Intro](#-intro)
- [➕ Requirements](#-requirements)
- [📦 Git Subtree or Git Submodule](#-git-subtree-or-git-submodule)
  - [🌲 Git Subtree](#-git-subtree)
    - [🌱 Adding a subtree](#-adding-a-subtree)
  - [👽️ Git Submodules](#️-git-submodules)
    - [💥 Adding a submodule](#-adding-a-submodule)
    - [✅ Initializing an existing submodule](#-initializing-an-existing-submodule)
- [📚 Using the library](#-using-the-library)

## 🎉 Intro

This repository contains a library with the protobuf messages used in the communication between the teams, [VSSSReferee](https://github.com/VSSSLeague/VSSReferee) and [TraveSim](https://github.com/ThundeRatz/travesim)/[TraveSim Adapters](https://github.com/ThundeRatz/travesim_adapters) (or [FIRASim](https://github.com/IEEEVSS/FIRASim)).

There is a `CMakeLists.txt` file in the root of this repository to make it easier to generate de header and source files for each `.proto` file.

Note: for now the `CMakeLists.txt` only supports generating for C++.

## ➕ Requirements

To be able to use the protobuf messages, make sure to have the [Google Protocol Buffers](https://github.com/protocolbuffers/protobuf) installed. Besides that, in order to use the `CMakeLists.txt` file, it is required to have [cmake](https://snapcraft.io/cmake) installed as well.

## 📦 Git Subtree or Git Submodule

This library functions may be added to your projetc as a subtree or a submodule. In this way it allows its development in parallel.

The difference between submodule and subtree, in a simplified explanation, is that using subtree you will have a copy of this library inside your project's repository, whille using submodules the files in this library will not be saved inside your project's repository, there will just be a referance to a specific commit of this library inside your project's repository and you will have to initialize the submodule as described below.

### 🌲 Git Subtree

To add this library as a subtree follow the steps below.

#### 🌱 Adding a subtree

Add the subtree by doing in the root of your repository:

```bash
git subtree add --prefix proto https://github.com/ThundeRatz/vsss_sim_pb_msgs.git main --squash
```

### 👽️ Git Submodules

To add this library as a submodule follow the steps below.

#### 💥 Adding a submodule

Add the submodule by doing in the root of your repository:

* With HTTPS:
```bash
git submodule add --name vsss_sim_pb_msgs https://github.com/ThundeRatz/vsss_sim_pb_msgs.git proto
```

* With SSH:
```bash
git submodule add --name vsss_sim_pb_msgs git@github.com:ThundeRatz/vsss_sim_pb_msgs.git proto
```

#### ✅ Initializing an existing submodule

When cloning a repository that already has submodules, it is necessary to clone the repositories of that submodule. This can be done in two ways, by cloning together with the project repository or after you have already cloned.

Example:

To clone together, run the following command, switching to the repository link of your project:

```bash
git clone --recurse-submodules git@github.com:ThundeRatz/travesim_adapters.git
```

To clone having already cloned the project repository, within it, you should do:

```bash
git submodule update --init
```

## 📚 Using the library

To use this library, add as a subdirectory it in the top-level `CMakeLists.txt` of your project, like this:

```cmake
add_subdirectory(proto)
```

Then simply link your executable with the library by doing:

```cmake
target_link_libraries(<your executable name>
  pb_msgs_lib
)
```

Lastly, in order to include the protobuf header in your executable, it is possible to include as below:

```cpp
#include "protobuf_file_name.pb.h"
```

For example, for the `vssref_placement.proto` message, you would do:

```cpp
#include "vssref_placement.pb.h"
```

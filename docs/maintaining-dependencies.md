
# Maintaining dependencies

## opentelemetry-proto

### Origin

The repository for opentelemetry-proto is:

* [repository](https://github.com/open-telemetry/opentelemetry-proto)

Check release notes at:

* [release-notes](https://github.com/open-telemetry/opentelemetry-proto/releases)

### Upgrade

When upgrading opentelemetry-proto to a newer release,
a few places in the code need adjustment.

In this example, we upgrade from 1.3.1 to 1.3.2

#### directory third_party/opentelemetry-proto

This is a `git submodule`, it needs to point to the new tag.

```shell
cd third_party/opentelemetry-proto
git log -1
```

The current submodule show something like:

```shell
commit b3060d2104df364136d75a35779e6bd48bac449a (HEAD, tag: v1.3.1)
Author: Damien Mathieu <42@dmathieu.com>
Date:   Thu Apr 25 17:55:35 2024 +0200

    generate profiles proto for CI (#552)
```

Pull new tags:

```shell
git pull --tag origin
```

Upgrade to a new tag:

```shell
git pull origin v1.3.2
```

Check the new state:

```shell
git log -1
```

```shell
commit 40b3c1b746767cbc13c2e39da3eaf1a23e54ffdd (HEAD, tag: v1.3.2)
Author: jack-berg <34418638+jack-berg@users.noreply.github.com>
Date:   Fri Jun 28 08:19:11 2024 -0500

    Prepare changelog for 1.3.2 release (#563)

    Co-authored-by: Armin Ruech <7052238+arminru@users.noreply.github.com>
```

Go back to the root of opentelemetry-cpp

```shell
cd ../..
git status
```

```shell
On branch upgrade_proto_1.3.2
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   third_party/opentelemetry-proto (new commits)
```

Add the upgraded submodule:

```shell
git add third_party/opentelemetry-proto
```

#### file third_party_release

Update the line pointing to the opentelemetry-proto tag.

```text
opentelemetry-proto=v1.3.2
```

Typical change:

```shell
[malff@malff-desktop opentelemetry-cpp]$ git diff third_party_release
diff --git a/third_party_release b/third_party_release
index 0bbf67f3..7362473f 100644
--- a/third_party_release
+++ b/third_party_release
@@ -19,7 +19,7 @@ benchmark=v1.8.3
 googletest=1.14.0
 ms-gsl=v3.1.0-67-g6f45293
 nlohmann-json=v3.11.3
-opentelemetry-proto=v1.3.1
+opentelemetry-proto=v1.3.2
 opentracing-cpp=v1.6.0
 prometheus-cpp=v1.2.4
 vcpkg=2024.02.14
```

#### file bazel/repository.bzl

Locate the entry for opentelemetry-proto:

```text
    # OTLP Protocol definition
    maybe(
        http_archive,
        name = "com_github_opentelemetry_proto",
        build_file = "@io_opentelemetry_cpp//bazel:opentelemetry_proto.BUILD",
        sha256 = "bed250ceec8e4a83aa5604d7d5595a61945059dc662edd058a9da082283f7a00",
        strip_prefix = "opentelemetry-proto-1.3.1",
        urls = [
            "https://github.com/open-telemetry/opentelemetry-proto/archive/v1.3.1.tar.gz",
        ],
    )
```

Update the URL to the new tag:

```text
        urls = [
            "https://github.com/open-telemetry/opentelemetry-proto/archive/v1.3.2.tar.gz",
        ],
```

Update strip_prefix to the new tag:

```text
        strip_prefix = "opentelemetry-proto-1.3.2",
```

Download the new URL:

```shell
wget https://github.com/open-telemetry/opentelemetry-proto/archive/v1.3.2.tar.gz
```

Run a checksum on the new file:

```shell
sha256sum v1.3.2.tar.gz
```

```shell
c069c0d96137cf005d34411fa67dd3b6f1f8c64af1e7fb2fe0089a41c425acd7  v1.3.2.tar.gz
```

Update the checksum in file bazel/repository.bzl:

```text
        sha256 = "c069c0d96137cf005d34411fa67dd3b6f1f8c64af1e7fb2fe0089a41c425acd7",
```

Typical change:

```shell
[malff@malff-desktop opentelemetry-cpp]$ git diff bazel/repository.bzl
diff --git a/bazel/repository.bzl b/bazel/repository.bzl
index bac1e45b..508b95a3 100644
--- a/bazel/repository.bzl
+++ b/bazel/repository.bzl
@@ -88,10 +88,10 @@ def opentelemetry_cpp_deps():
         http_archive,
         name = "com_github_opentelemetry_proto",
         build_file = "@io_opentelemetry_cpp//bazel:opentelemetry_proto.BUILD",
-        sha256 = "bed250ceec8e4a83aa5604d7d5595a61945059dc662edd058a9da082283f7a00",
-        strip_prefix = "opentelemetry-proto-1.3.1",
+        sha256 = "c069c0d96137cf005d34411fa67dd3b6f1f8c64af1e7fb2fe0089a41c425acd7",
+        strip_prefix = "opentelemetry-proto-1.3.2",
         urls = [
-            "https://github.com/open-telemetry/opentelemetry-proto/archive/v1.3.1.tar.gz",
+            "https://github.com/open-telemetry/opentelemetry-proto/archive/v1.3.2.tar.gz",
         ],
     )
```

#### file cmake/opentelemetry-proto.cmake

Update the tag in the CMake logic:

```cmake
        set(opentelemetry-proto "v1.3.2")
```

Typical change:

```shell
[malff@malff-desktop opentelemetry-cpp]$ git diff cmake/opentelemetry-proto.cmake
diff --git a/cmake/opentelemetry-proto.cmake b/cmake/opentelemetry-proto.cmake
index 19516c3b..dd6213c1 100644
--- a/cmake/opentelemetry-proto.cmake
+++ b/cmake/opentelemetry-proto.cmake
@@ -49,7 +49,7 @@ else()
          "opentelemetry-proto=[ \\t]*([A-Za-z0-9_\\.\\-]+)")
         set(opentelemetry-proto "${CMAKE_MATCH_1}")
       else()
-        set(opentelemetry-proto "v1.3.1")
+        set(opentelemetry-proto "v1.3.2")
       endif()
       unset(OTELCPP_THIRD_PARTY_RELEASE_CONTENT)
     endif()
```

If opentelemetry-proto contains new files,
the makefile needs to be adjusted to build the new code.

#### file MODULE.bazel

Make sure the new tag is available in bazel central:

* [bazel-central](https://registry.bazel.build/modules/opentelemetry-proto)

If missing, file a PR to add it, or contact the maintainer:

* [repository](https://github.com/bazelbuild/bazel-central-registry/tree/main/modules/opentelemetry-proto)

Update the opentelemetry-proto version to the new tag:

```text
bazel_dep(name = "opentelemetry-proto", version = "1.3.2", repo_name = "com_github_opentelemetry_proto")
```

Typical change:

```shell
[malff@malff-desktop opentelemetry-cpp]$ git diff MODULE.bazel
diff --git a/MODULE.bazel b/MODULE.bazel
index 7b84c2b7..3161ffb1 100644
--- a/MODULE.bazel
+++ b/MODULE.bazel
@@ -13,7 +13,7 @@ bazel_dep(name = "bazel_skylib", version = "1.5.0")
 bazel_dep(name = "curl", version = "8.4.0")
 bazel_dep(name = "grpc", version = "1.62.1", repo_name = "com_github_grpc_grpc")
 bazel_dep(name = "nlohmann_json", version = "3.11.3", repo_name = "github_nlohmann_json")
-bazel_dep(name = "opentelemetry-proto", version = "1.3.1", repo_name = "com_github_opentelemetry_proto")
+bazel_dep(name = "opentelemetry-proto", version = "1.3.2", repo_name = "com_github_opentelemetry_proto")
 bazel_dep(name = "opentracing-cpp", version = "1.6.0", repo_name = "com_github_opentracing")
 bazel_dep(name = "platforms", version = "0.0.8")
 bazel_dep(name = "prometheus-cpp", version = "1.2.4", repo_name = "com_github_jupp0r_prometheus_cpp")
```
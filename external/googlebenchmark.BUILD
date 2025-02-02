load("@rules_cc//cc:defs.bzl", "cc_library")

licenses(["notice"])

config_setting(
    name = "qnx",
    constraint_values = ["@platforms//os:qnx"],
    values = {
        "cpu": "x64_qnx",
    },
    visibility = [":__subpackages__"],
)

config_setting(
    name = "windows",
    constraint_values = ["@platforms//os:windows"],
    values = {
        "cpu": "x64_windows",
    },
    visibility = [":__subpackages__"],
)

cc_library(
    name = "benchmark",
    srcs = glob(
        [
            "src/*.cc",
            "src/*.h",
        ],
        exclude = ["src/benchmark_main.cc"],
    ),
    hdrs = ["include/benchmark/benchmark.h"],
    linkopts = select({
        ":windows": ["-DEFAULTLIB:shlwapi.lib"],
        "//conditions:default": ["-pthread"],
    }),
    copts=["-DNDEBUG"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "benchmark_main",
    srcs = ["src/benchmark_main.cc"],
    hdrs = ["include/benchmark/benchmark.h"],
    copts=["-DNDEBUG"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [":benchmark"],
)

cc_library(
    name = "benchmark_internal_headers",
    hdrs = glob(["src/*.h"]),
    copts=["-DNDEBUG"],
    visibility = ["//test:__pkg__"],
)

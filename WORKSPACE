workspace(name = 'libmicrohttpd-bazel-example')

load('@bazel_tools//tools/build_defs/repo:http.bzl', 'http_archive')

ALL_CONTENT = 'filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])'

ROOT_3P = 'file://' + __workspace_dir__ + '/3p/'

http_archive(
    name = 'absl',
    url = ROOT_3P + 'abseil-cpp-master.tar.xz',
    strip_prefix = 'abseil-cpp-master',
    sha256 = '2efbd20528623dbce8eb5aeb3f91f037259034c95a972b000e7f051dedc63d05',
)

http_archive(
    name = 'libmicrohttpd',
    build_file_content = ALL_CONTENT,
    url = ROOT_3P + 'libmicrohttpd-0.9.72.tar.xz',
    strip_prefix = 'libmicrohttpd-0.9.72',
    sha256 = '4eb9e02c7e91b4f630d08cf7b4443ca2286f78f7e4390c8ba8c0d715f69deffa',
)

http_archive(
    name = 'rules_foreign_cc',
    url = ROOT_3P + 'rules_foreign_cc-master.tar.xz',
    strip_prefix = 'rules_foreign_cc-master',
    sha256 = '1a16c23c5f152dc866851efec06f16cccada682a59a84c2b19de05eb3440b50f',
)
load('@rules_foreign_cc//:workspace_definitions.bzl', 'rules_foreign_cc_dependencies')
rules_foreign_cc_dependencies(register_default_tools = True)

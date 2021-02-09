workspace(name = 'libmicrohttpd-bazel-example')

load('@bazel_tools//tools/build_defs/repo:http.bzl', 'http_archive')

ALL_CONTENT = 'filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])'

ROOT_3P = 'file://' + __workspace_dir__ + '/3p/'

http_archive(
    # Always use the same name as in the WORKSPACE file of the external project. i.e. com_google_absl instead of absl.
    name = 'com_google_absl',
    url = ROOT_3P + 'abseil-cpp-master.tar.xz',
    strip_prefix = 'abseil-cpp-master',
    sha256 = '2efbd20528623dbce8eb5aeb3f91f037259034c95a972b000e7f051dedc63d05',
)

http_archive(
    name = 'com_google_tcmalloc',
    url = ROOT_3P + 'tcmalloc-master.tar.xz',
    strip_prefix = 'tcmalloc-master',
)

http_archive(
    name = 'libmicrohttpd',
    build_file_content = ALL_CONTENT,
    url = ROOT_3P + 'libmicrohttpd-0.9.72.tar.xz',
    strip_prefix = 'libmicrohttpd-0.9.72',
    sha256 = '4eb9e02c7e91b4f630d08cf7b4443ca2286f78f7e4390c8ba8c0d715f69deffa',
)

http_archive(
    name = 'boringssl',
    url = ROOT_3P + 'chromium-stable-with-bazel.tar.xz',
    sha256 = 'f3055d4f0fa72275b8c5fd5561c8e6b7546b49a19f7b248bc92f9584ccdd62eb',
)

http_archive(
    name = 'rules_foreign_cc',
    url = ROOT_3P + 'rules_foreign_cc-master.tar.xz',
    strip_prefix = 'rules_foreign_cc-master',
    sha256 = '1a16c23c5f152dc866851efec06f16cccada682a59a84c2b19de05eb3440b50f',
)
load('@rules_foreign_cc//:workspace_definitions.bzl', 'rules_foreign_cc_dependencies')
rules_foreign_cc_dependencies(register_default_tools = True)

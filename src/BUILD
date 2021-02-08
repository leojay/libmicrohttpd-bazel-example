load('@rules_foreign_cc//tools/build_defs:configure.bzl', 'configure_make')

package(default_visibility = ['//visibility:public'])

configure_make(
    name = 'libmicrohttpd',
    lib_source = '@libmicrohttpd//:all',
    configure_options = ['--disable-https', '--disable-nls', '--disable-doc', '--disable-examples', '--disable-curl', '--disable-shared'],
)

cc_binary(
    name = 'hello-world',
    srcs = ['hello_world.cc'],
    deps = [
        ':libmicrohttpd',
        '@absl//absl/debugging:failure_signal_handler',
        '@absl//absl/debugging:symbolize',
    ],
    # Uncomment this to enable full static link.
    # features = ['fully_static_link'],
)

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
        '@boringssl//:crypto',
        '@com_google_absl//absl/debugging:failure_signal_handler',
        '@com_google_absl//absl/debugging:symbolize',
        '@com_google_absl//absl/strings',
    ],
    # Uncomment this to enable full static link.
    # features = ['fully_static_link'],

    # Comment this out to use system malloc runtime.
    malloc = '@com_google_tcmalloc//tcmalloc',
)

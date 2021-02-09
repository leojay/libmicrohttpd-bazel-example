#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "absl/debugging/failure_signal_handler.h"
#include "absl/debugging/symbolize.h"
#include "absl/strings/escaping.h"
#include "absl/strings/match.h"
#include "absl/strings/numbers.h"
#include "absl/strings/string_view.h"
#include "microhttpd.h"
#include "openssl/digest.h"

#define PAGE \
  "<html><head><title>libmicrohttpd demo</title></head><body>Query string for &quot;%s&quot; was &quot;%s&quot;</body></html>"

namespace {
MHD_Response* g_empty_response;
const absl::string_view kHttpMethodGet = MHD_HTTP_METHOD_GET;

void init_global_responses() {
    g_empty_response = MHD_create_response_from_buffer(0, (void*)"", MHD_RESPMEM_PERSISTENT);
}

MHD_Result method_not_allowed(MHD_Connection* connection) {
    return MHD_queue_response(connection, MHD_HTTP_METHOD_NOT_ALLOWED, g_empty_response);
}

MHD_Result not_found(MHD_Connection* connection) {
    return MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, g_empty_response);
}
}

static enum MHD_Result
ahc_echo(void* cls,
         MHD_Connection* connection,
         const char* url,
         const char* method,
         const char* version,
         const char* upload_data, size_t* upload_data_size, void** ptr) {
    static int dummy_ptr;
    const char* fmt = (const char*) cls;
    const char* val;
    char* me;
    MHD_Response* response;
    enum MHD_Result ret;
    (void) url;               /* Unused. Silent compiler warning. */
    (void) version;           /* Unused. Silent compiler warning. */
    (void) upload_data;       /* Unused. Silent compiler warning. */
    (void) upload_data_size;  /* Unused. Silent compiler warning. */

    if (method != kHttpMethodGet) {
        return method_not_allowed(connection);
    }
    if (&dummy_ptr != *ptr) {
        /* do never respond on first call */
        *ptr = &dummy_ptr;
        return MHD_YES;
    }

    if (absl::EndsWithIgnoreCase(url, ".ico")) {
        return not_found(connection);
    }

    *ptr = NULL;                  /* reset when done */
    val = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "q");
    me = (char*) malloc(snprintf(NULL, 0, fmt, "q", val) + 1);
    if (!me)
        return MHD_NO;
    sprintf(me, fmt, "q", val);
    response = MHD_create_response_from_buffer(strlen(me), me,
                                               MHD_RESPMEM_MUST_FREE);
    if (!response) {
        free(me);
        return MHD_NO;
    }
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

void boringssl_sha256_demo() {
    std::string s = "hello world!";
    uint8_t digest[EVP_MAX_MD_SIZE];
    const EVP_MD *hash = EVP_sha256();
    unsigned int digest_len = EVP_MAX_MD_SIZE;
    if (EVP_Digest(s.data(), s.length(), digest, &digest_len, hash, nullptr) != 0) {
        std::string hex_digest = absl::BytesToHexString(absl::string_view((const char*) digest, digest_len));
        printf("Digest is: %s\n", hex_digest.c_str());
    } else {
        printf("Failed to calculate digest.\n");
    }
}


int main(int argc, char* const* argv) {
    absl::InitializeSymbolizer(argv[0]);
    absl::InstallFailureSignalHandler({});

    boringssl_sha256_demo();

    if (argc != 2) {
        printf("%s PORT\n", argv[0]);
        return 1;
    }

    init_global_responses();

    int port = 0;
    if (!absl::SimpleAtoi(argv[1], &port) || port < 0 || port > UINT16_MAX) {
        printf("%s PORT\n", argv[0]);
        return 1;
    }

    MHD_Daemon* d;
    d = MHD_start_daemon(MHD_USE_EPOLL | MHD_USE_INTERNAL_POLLING_THREAD,
                         (uint16_t) port,
                         NULL, NULL, &ahc_echo, (void*) PAGE,
                         MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int) (120 /* seconds */),
                         MHD_OPTION_THREAD_POOL_SIZE, (unsigned int) 8,
                         MHD_OPTION_END);
    if (!d)
        return 1;
    printf("Listening on port %d, lib version: %s\n", port, MHD_get_version());
    (void) getc(stdin);
    MHD_stop_daemon(d);
    return 0;
}

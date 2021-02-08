#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <microhttpd.h>
#include "absl/debugging/failure_signal_handler.h"
#include "absl/debugging/symbolize.h"

#define PAGE \
  "<html><head><title>libmicrohttpd demo</title></head><body>Query string for &quot;%s&quot; was &quot;%s&quot;</body></html>"

static enum MHD_Result
ahc_echo(void* cls,
         struct MHD_Connection* connection,
         const char* url,
         const char* method,
         const char* version,
         const char* upload_data, size_t* upload_data_size, void** ptr) {
    static int aptr;
    const char* fmt = (const char*) cls;
    const char* val;
    char* me;
    struct MHD_Response* response;
    enum MHD_Result ret;
    (void) url;               /* Unused. Silent compiler warning. */
    (void) version;           /* Unused. Silent compiler warning. */
    (void) upload_data;       /* Unused. Silent compiler warning. */
    (void) upload_data_size;  /* Unused. Silent compiler warning. */

    if (strcmp(method, MHD_HTTP_METHOD_GET))
        return MHD_NO;              /* unexpected method */
    if (&aptr != *ptr) {
        /* do never respond on first call */
        *ptr = &aptr;
        return MHD_YES;
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


int main(int argc, char* const* argv) {
    struct MHD_Daemon* d;
    int port;

    absl::InitializeSymbolizer(argv[0]);
    absl::InstallFailureSignalHandler({});

    if (argc != 2) {
        printf("%s PORT\n", argv[0]);
        return 1;
    }
    port = atoi(argv[1]);
    if ((port < 0) ||
            (port > UINT16_MAX)) {
        printf("%s PORT\n", argv[0]);
        return 1;
    }
    d = MHD_start_daemon(MHD_USE_EPOLL | MHD_USE_INTERNAL_POLLING_THREAD | MHD_USE_ERROR_LOG,
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


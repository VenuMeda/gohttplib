#include <stdio.h>
#include "../../build/libgohttp.h"

void handler(ResponseWriterPtr w, Request *req)
{
    printf("handler: %s %s\n%s\n\n%s\n", req->Method, req->URL, req->Headers, req->Body);

    char *buf = "Hello, world";
    int n = ResponseWriter_Write(w, buf, 12);

    if (n == EOF) {
        printf("handler: Failed to write.\n");
        ResponseWriter_WriteHeader(w, 500);
        return;
    }

    printf("handler: Wrote %d bytes.\n", n);
}

int main()
{
    HandleFunc("/", &handler);
    printf("Listening on :8000\n");
    ListenAndServe(":8000");
    return 0;
}

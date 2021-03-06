/*
 * 	 @author 	 f1est 
 * 	 telegram: 	 @F1estas (https://t.me/F1estas) 
 * 	 e-mail: 	 www-b@mail.ru 
 */
 
#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "common.h"
#include "hashmap.h"
#include "cJSON.h"

typedef struct http_proxy_core_s http_proxy_core_t;
struct http_proxy_core_s {
        struct evhttp *http_server;
        struct evhttp *http_server_2; /* using when listen HTTP and HTTPS */
        struct evhttp_bound_socket *evhttp_socket;
        struct evhttp_bound_socket *evhttp_socket_2; /* using when listen HTTP and HTTPS */
        const char *redirect_address;  /* using for redirect requests when listen HTTP and HTTPS */
        hashtable_t *SIDs; 
        cJSON *json_security_headers;
};

typedef struct req_proxy_to_server_s req_proxy_to_server_t;
struct req_proxy_to_server_s {
        struct evhttp_connection *serv_conn;
        struct evhttp_connection *client_conn;
        struct evhttp_request *req_proxy_to_server;
        struct evhttp_request *req_client_to_proxy;
        struct event *cleanup;
        struct evhttp_uri *uri;

        /* table will be filled after parsing a Cookie-header */
        hashtable_t *cookies_tbl;

        /* If a new request contains EmbeddedSID, param hasSID will be TRUE (1). 
         * Hence, we know should create and add EmbeddedSID to response or not */
        base_t *hasSID; 
};

void accept_cb(struct evconnlistener *listener, evutil_socket_t fd,struct sockaddr *a, int slen, void *p);
http_proxy_core_t *http_core_init(struct evconnlistener *listener,struct evconnlistener *second_listener, const char* redirect_address);
void free_proxy_core(http_proxy_core_t *core);

#endif /* TRANSPORT_H */

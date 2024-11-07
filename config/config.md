server {
    listen 80;
    server_name defaultserver;

    root /webserv/www/html;
    max_body_size 10000000;

    error_page 404 /404.html;
    error_page 500 /50x.html;
    error_page 502 /50x.html;
    error_page 503 /50x.html;
    error_page 504 /50x.html;

    location / {
        index index.html;
        allowed_methods GET POST DELETE;
        autoindex on;
    }

    location /uploads {
        allowed_methods PUT;
        upload_store /webserv/www/uploads;
    }

    location /cgi-bin {
        allowed_methods GET POST;
        autoindex off;
        cgi_root /webserv/cgi-bin;
    }

    location /redirect {
        return 301 http://example.com;
    }
}

server {
    listen 7777;
    server_name example.com;

    root /webserv/www/example;
    max_body_size 500000;

    location / {
        index index.html;  
        allowed_methods GET;
        autoindex on;
    }
}

server {
    listen 8888;
    server_name _;

    root ./www/html;
    max_body_size 50000000000;

    error_page 403 /403.html;
    error_page 404 /404.html;
    error_page 405 /405.html;
    error_page 413 /413.html;
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
        allowed_methods PUT DELETE GET;
        upload_store ./storage;
        autoindex on;
    }

    location /cgi-bin {
        allowed_methods GET POST;
        cgi_root ./cgi-bin;
    }

    location /redirect {
        allowed_methods GET PUT POST DELETE;
        return 301 http://example.com;
    }
}

server {
    listen 7777;
    server_name example.com;

    root ./www/example;
    max_body_size 500000;

    location / {
        index index.html;
        allowed_methods GET;
        autoindex on;
    }
}

server {
    listen 7777;
    server_name _;

    root ./www/test;
    max_body_size 500000;

    location / {
        index index.html;
        allowed_methods GET;
        autoindex on;
    }
}

server {
    listen 8080;
    server_name example.com;
    client_max_body_size 10M;

    location / {
        root /var/www/html;
        index index.html index.htm;
        allowed_methods GET POST PUT DELETE;
    }

    location /public_files {
        root /var/www/public;
        autoindex on;
        allowed_methods GET;
    }

    location /uploads {
        root /var/www/uploads;
        client_max_body_size 20M;
        allowed_methods GET POST PUT DELETE;
        autoindex off;
    }

    location /cgi-bin {
        root /var/www/cgi-bin;
        allowed_methods GET POST;
        cgi_pass .php /usr/bin/php-cgi;
        cgi_pass .py /usr/bin/python;
    }

    location /redirect {
        return 301 http://www.example.com$request_uri;
    }

    location /temp_redirect {
        return 302 http://www.example.com$request_uri;
    }

    error_page 404 /custom_404.html;
    location = /custom_404.html {
        root /var/www/error_pages;
        internal;
    }
}

server {
    listen 8081;
    server_name test.example.com;

    location / {
        root /var/www/test;
        index test.html;
        allowed_methods GET;
    }

    location /api {
        root /var/www/api;
        allowed_methods GET POST PUT DELETE;
        autoindex off;
    }

    location /test_autoindex {
        root /var/www/test_autoindex;
        autoindex on;
        allowed_methods GET;
    }
}

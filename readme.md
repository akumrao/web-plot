For web plot Instructions:
-------------

1. Install Emscripten:

    http://emscripten.org

2. Clone this repo:

    ```https://github.com/akumrao/web-plot.git```
    
    ```cd web-plot``
    
3. Build index.js and index.wasm:

    ```emcc *.cpp -s WASM=1 -s USE_SDL=2 -O3 -o index.js```
or    make wasm


4. Open index.html in a web browser. You should see a moving blue square in a red square:

    To run make run
    with Python 2: ```python -m SimpleHTTPServer 8080```
    
    with Python 3: ```python -m http.server 8080```

    and then open this URL:

    http://localhost:8080/
    
```

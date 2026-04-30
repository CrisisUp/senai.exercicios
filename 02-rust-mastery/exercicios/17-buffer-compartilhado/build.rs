fn main() {
    cc::Build::new()
        .file("src/buffer_handler.c")
        .compile("bufferhandler"); 
}

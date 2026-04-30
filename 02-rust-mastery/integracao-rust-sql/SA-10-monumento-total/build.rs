fn main() {
    // Compila o Driver em C++ e linka com o Rust
    cc::Build::new()
        .cpp(true) // Habilita modo C++
        .file("src/driver_hardware.cpp")
        .compile("dronehardware");
}

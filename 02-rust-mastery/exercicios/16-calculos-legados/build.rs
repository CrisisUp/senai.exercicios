fn main() {
    // Compila o arquivo C e linka com o binário Rust
    cc::Build::new()
        .file("src/math_motor.c")
        .compile("mathmotor");
}

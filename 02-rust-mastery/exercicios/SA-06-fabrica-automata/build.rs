fn main() {
    cc::Build::new()
        .file("src/stress_test.c")
        .compile("stresstest");
}

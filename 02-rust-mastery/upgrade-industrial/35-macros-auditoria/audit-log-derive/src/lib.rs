#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file lib.rs
 * @brief Implementação da Macro Procedural AuditLog.
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

extern crate proc_macro;
use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, DeriveInput, Data, Fields};

#[proc_macro_derive(AuditLog)]
pub fn audit_log_derive(input: TokenStream) -> TokenStream {
    // 1. Analisa o código da Struct (Parsing)
    let input = parse_macro_input!(input as DeriveInput);
    let name = &input.ident;

    // 2. Extrai os nomes dos campos para gerar o log
    let fields_capture = match &input.data {
        Data::Struct(data) => {
            match &data.fields {
                Fields::Named(fields) => {
                    let recurse = fields.named.iter().map(|f| {
                        let name = &f.ident;
                        quote! {
                            format!("{}: {:?}", stringify!(#name), self.#name)
                        }
                    });
                    quote! { vec![#(#recurse),*].join(", ") }
                }
                _ => quote! { String::from("Campos não nomeados") },
            }
        }
        _ => panic!("AuditLog só pode ser usado em Structs"),
    };

    // 3. Gera o novo código Rust (Code Generation)
    let expanded = quote! {
        impl Auditoria for #name {
            fn gerar_log(&self) -> String {
                format!("\x1b[1;33m[AUDITORIA-AUTO]\x1b[0m Struct {}: {{ {} }}", stringify!(#name), #fields_capture)
            }
        }
    };

    // 4. Devolve o código gerado para o compilador
    TokenStream::from(expanded)
}

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */
/*
 * RESUMO TEÓRICO
 * Implementação em Rust seguindo as diretrizes de segurança e performance.
 */

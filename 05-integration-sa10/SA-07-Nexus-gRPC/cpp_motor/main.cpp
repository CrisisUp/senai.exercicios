/**
 * @file main.cpp
 * @brief Servidor gRPC de Telemetria (C++ Motor).
 * @author Engenheiro de Elite
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "telemetria.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using logispeed::TelemetriaService;
using logispeed::DroneRequest;
using logispeed::DroneResponse;

// Implementação do Serviço Definido no Proto
class TelemetriaServiceImpl final : public TelemetriaService::Service {
    Status ObterStatus(ServerContext* context, const DroneRequest* request,
                       DroneResponse* reply) override {
        std::cout << "\x1b[1;34m[C++ MOTOR]\x1b[0m Recebida solicitação para o Drone: " << request->drone_id() << std::endl;
        
        reply->set_msg("Conexão estável via satélite gRPC.");
        reply->set_operacional(true);
        
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    TelemetriaServiceImpl service;

    ServerBuilder builder;
    // Escuta na porta 50051 sem autenticação (para este desafio de laboratório)
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "\x1b[1;32m[SYSTEM]\x1b[0m Servidor gRPC C++ escutando em " << server_address << std::endl;

    server->Wait();
}

int main() {
    RunServer();
    return 0;
}

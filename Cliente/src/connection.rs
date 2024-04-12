extern crate log;
use std::time::Duration;
use std::thread::sleep;
use std::net::TcpStream;
use ini::configparser::ini::Ini;
use log::{error,debug, trace};

//Conexión cliente-servidor
//Se intenta realizar una conexión entre el cliente y el server
pub fn connect_client_to_server() -> std::io::Result<TcpStream> {

    loop {
        log::trace!("Iniciando intento de conexión con el servidor");
        match connect() {
            Ok(stream) => {
                println!("¡Conexión exitosa con el servidor!");
                trace!("Conexión establecida con el servidor.");
                return Ok(stream);  //Se rompe el bucle si la conexión si se  logra la conexión
            }
            Err(err) => {
                error!("Conexión no establecida con el servidor.: {}", err); //Error que provoca la no conexión
                sleep(Duration::from_secs(3)); //Tiempo de espera hasta intentar conectarse otra vez
            }
        }
    }
}

//Carga la info del server
//Nota:El path de la línea 36 se debe cambiar acorde a donde se encuentra la carpeta que tiene el .ini
fn load_server_info() -> Option<(String, u16)> {
    let mut config = Ini::new();
    if let Err(e) = config.load("/home/fabiangj/QtCMP/config.ini") { //Busca el .ini del server
    error!("Error al cargar el archivo de configuración: {}", e); //Mensaje de error en caso de que no se cargo la info .ini del server
        return None;
    }
    //Obtiene a ip del .ini
    let address_server = match config.get("server", "address") { //Obtiene a ip del .ini
        Some(address) => {  //Guarda la ip
        trace!("Se ha encontrado la dirección IP:{}",address); //Encuentra la ip exitosamente
            address
        }
        None => {
            error!("Dirección IP del servidor no encontrada en el archivo .ini."); //Falla al buscar la ip
            return None;
        }
    };
    let port_server = match config.get("server", "port") {
        Some(port) => match port.parse::<u16>() {
            Ok(parsed_port) => {trace!("Se ha encontrado el puerto:{}" ,parsed_port);
                parsed_port}
            Err(_) => {
                error!("Puerto del servidor no válido en el archivo .ini."); //No cumple u16
                return None;
            }
        },
        None => {
            error!("Puerto del servidor no encontrado en el archivo .ini.");
            return None;
        }
    };
    Some((address_server, port_server)) //Puerto e IP del server
}

//Funcionar para realizar la conexión cliente/servidor
fn connect() -> std::io::Result<TcpStream> {
    //  Carga la info del server
    if let Some((address, port)) = load_server_info() {
        println!("Intentando conectar con el servidor en {}:{}", address, port);
        debug!("Conectando con el servidor en {}:{}", address, port);
        let server_socket = format!("{}:{}", address, port);
        //Intenta establecer una conexión TCP con el server
        match TcpStream::connect(server_socket) {
            Ok(stream) => Ok(stream),
            Err(e) => Err(e),
        }
    } else {
        error!("No se pudo obtener la información del servidor.");
        Err(std::io::Error::new(std::io::ErrorKind::Other, "Configuración del servidor no encontrada"))
    }
}

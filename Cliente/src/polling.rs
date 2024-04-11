use ini::configparser::ini::Ini;
use log::{error,debug, trace};
use std::net::TcpStream;
use std::time::Duration;
use std::thread::sleep;
use serde_json;
use serde::{Deserialize,Serialize};
use std::io::{Write, Read};

//Carga el valor del tiempo de .ini
fn load_client_info()-> Option<u16> {
    let mut config = Ini::new();
    if let Err(e) = config.load("/home/joaquin/Cliente/config.ini") { //Busca el .ini sel cliente
    error!("Error al cargar el archivo de configuración: {}", e); //Mensaje de error en caso de que no se encuentre el .ini
        return None;
    }
//Obtiene el tiempo
    let time_polling = match config.get("polling", "tiempo") { //Obtiene el tiempo
        Some (tiempo) => match tiempo.parse::<u16>(){  //Guarda time
            Ok(parsed_time) => {trace!("Se ha encontrado el valor de tiempo:{}" ,parsed_time);
                parsed_time}
            Err(_) => {
                error!("Valor de tiempo no válido en el archivo .ini."); //No cumple u16
                return None;
            }
        },
        None => {
            error!("Valor de tiempo no encontrado"); //Fallo al encontrar tiempo en polling
            return None;
        }
    };
    Some(time_polling)
}

//Funci[on que solicita al server una actualizacion de la playlist
pub fn polling(stream: &mut TcpStream)-> Option<Vec<String>> {
    loop {
        if let Some(tiempo )= load_client_info() {
            debug!("Solicitud Enviada: Esperando actualización del servidor.");

            match get_playlist(stream) {
                Some(playlist) => {
                    debug!("Actualización Recibida: Playlist actualizada {:?}", playlist);
                },
                None => {
                    error!("Solicitud no procesada: No se pudo obtener el playlist actualizado.");
                }
            }

            sleep(Duration::from_secs(tiempo as u64)); // Espera antes de la próxima actualización
        }
    }
}
//Mediante el comando enviado se obtiente la playlist
pub fn get_playlist(stream: &mut TcpStream) -> Option<Vec<Song>>{
    let command = "Get-Playlist"; //Comando para obtener la Playlist
    if let Err(e) = stream.write_all(command.as_bytes()) {//Se envía al server
    error!("Error al enviar el comando al servidor: {}", e);
        return None;
    }
    let mut buffer = String::new();
    if let Err(e) = stream.read_to_string(&mut buffer) {
        error!("Error al recibir respuesta del servidor: {}", e);
        return None;
    }

    if let Ok(response) = serde_json::from_str::<ServerResponse>(&buffer) { //Analiza la respuesta en Json mandada por el server
        if response.status == "OK" && response.command == "playlist" {//Si se recibe la peticion correctamente
            return response.playlist; //Se muestra el playlist (id, song, artist)
        } else {
            error!("Respuesta no válida: {:?}", response);//Si la respuesta recibida no es válida
        }
    } else {
        error!("Error"); //Fallo del Json
    }
    None

}
pub fn send_vote(stream: &mut TcpStream, song: &str, vote: &str){
    let vote_message = VoteMessage {
        song: String::from(song),
        vote: String::from(vote),
    };
    // Serializar el mensaje de voto a JSON
    let serialized_vote_message = serde_json::to_string(&vote_message).unwrap();

    if let Err(e) = stream.write_all(serialized_vote_message.as_bytes()) {
        error!("Error al enviar el voto al servidor: {}", e);
    }
}
#[derive(Debug,Deserialize)]
pub struct Song {
    //Datos de cada canción
    pub id: u64,
    pub title: String,
    pub artist: String,
}

#[derive(Serialize)]
pub struct VoteMessage {
    pub song: String,
    pub vote: String,
}
#[derive(Debug, Deserialize)]
pub struct ServerResponse {
    // Datos que representan el playlist recibidp
    pub status: String,
    pub command: String,
    pub playlist: Option<Vec<Song>>,
}


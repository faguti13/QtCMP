mod connection;
mod polling;

use fltk::{app, prelude::*, window::Window, group::Group, button::Button};
use fltk::enums::FrameType;
use fltk::enums::Color;
use std::thread;
use polling::send_vote;
use crate::polling::polling;
use std::sync::{Arc, Mutex};
use polling::{get_playlist, print_playlist};


fn main() {
    //Config del nivel de log
    env_logger::builder()
        .filter_level(log::LevelFilter::Trace) //Filtra apartir de Trace (nivel más bajo)
        .init();

    let mut stream = match connection::connect_client_to_server() {
        Ok(stream) => stream
        ,
        Err(err) => {
            eprintln!("Error al conectar con el servidor: {}", err);
            return;
        }
    };

    let app = app::App::default();
    let mut wind = Window::new(400, 100, 450, 600, "Cliente");

    // Crear un contenedor para la lista de canciones
    let mut group = Group::new(10, 10, 680, 600, "");
    group.set_frame(FrameType::FlatBox);

    // Ejemplo de lista de canciones obtenidas del servidor
    let songs = vec![
        "Canción 1",
        "Canción 2",
        "Canción 3",
        "Canción 4",
        "Canción 5",
        "Canción 6",
        "Canción 7",
        "Canción 8",
        "Canción 9",
        "Canción 10",
    ];

    // Definir las posiciones iniciales
    let mut x_position = 20;
    let mut y_position = 50;
    let item_height = 40;
    let item_width = 400;
    let button_width = 50;
    let spacing = 10;

    // Iterar sobre la lista de canciones y agregar botones de up-vote y down-vote
    for song in songs {
        let mut cloned_stream = Arc::new(Mutex::new(stream.try_clone().expect("Failed to clone TcpStream")));


        let mut button_up = Button::new(x_position, y_position, button_width, item_height, "▲");
        let mut button_down = Button::new(x_position + item_width - button_width, y_position, button_width, item_height, "▼");
        let mut button_song = Button::new(x_position + button_width, y_position, item_width - 2 * button_width, item_height, song);

        button_up.set_color(Color::from_u32(0x649632));
        button_down.set_color(Color::from_u32(0x963232));

        button_up.set_callback({
            let cloned_stream = Arc::clone(&cloned_stream);
            let song = song.to_string(); // Clonar la cadena de la canción para usarla en el cierre
            move |_| {
                println!("Up-Vote para la canción: {}", song);
                send_vote(&mut cloned_stream.lock().unwrap(), &song, "Up-Vote");//Envia el voto al server
            }
        });

        button_down.set_callback({
            let cloned_stream = Arc::clone(&cloned_stream);
            let song = song.to_string(); // Clonar la cadena de la canción para usarla en el cierre
            move |_| {
                println!("Down-Vote para la canción: {}", song);
                send_vote(&mut cloned_stream.lock().unwrap(), &song, "Down-Vote"); //Envia el voto al server
            }
        });

        // Aumentar la posición en y para el próximo conjunto de elementos
        y_position += item_height + spacing;


        // Agregar botones y canción al contenedor
        group.add(&button_up);
        group.add(&button_down);
        group.add(&button_song);
    }
    wind.end();
    wind.show();

    thread::spawn(move || {
        // Conexión al servidor dentro del hilo
        let mut stream = match connection::connect_client_to_server() {
            Ok(stream) => stream,
            Err(err) => {
                eprintln!("Error al conectar con el servidor: {}", err);
                return;
            }
        };
        
        // Llamar a la función de polling
        polling(&mut stream);
    
        // Llamar a la función get_playlist para obtener la lista de reproducción
        let playlist = match get_playlist(&mut stream) {
            Some(playlist) => playlist,
            None => {
                eprintln!("Error al obtener la lista de reproducción.");
                return;
            }
        };
    });

    app.run().unwrap();

}

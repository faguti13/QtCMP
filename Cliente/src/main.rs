use fltk::{app, prelude::*, window::Window, group::Group, button::Button};
use fltk::enums::FrameType;
use fltk::enums::Color;
use ini::ini;

fn main() {
    let app = app::App::default();
    let mut wind = Window::new(400, 100, 900, 600, "Cliente");

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
                     "Canción 11"
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
        let mut button_up = Button::new(x_position, y_position, button_width, item_height, "▲");
        let mut button_down = Button::new(x_position + item_width - button_width, y_position, button_width, item_height, "▼");
        let mut button_song = Button::new(x_position + button_width, y_position, item_width - 2 * button_width, item_height, song);

        button_up.set_color(Color::from_u32(0x649632));
        button_down.set_color(Color::from_u32(0x963232));

        button_up.set_callback(move |_| {
            // Lógica para up-vote
            println!("Up-vote para {}", song);
        });

        button_down.set_callback(move |_| {
            // Lógica para down-vote
            println!("Down-vote para {}", song);
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

    app.run().unwrap();
}

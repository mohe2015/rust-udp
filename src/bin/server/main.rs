use tokio::net::UdpSocket;
use std::io;
use socket2::{Socket, Domain, Type};
use std::net::{SocketAddr};

async fn process() -> io::Result<()> {
    let address: SocketAddr = "[::]:1337".parse().unwrap();
    let address = address.into();

    let socket2_socket = Socket::new(Domain::IPV6, Type::DGRAM, None)?;
    socket2_socket.set_nonblocking(true)?;
    socket2_socket.set_reuse_address(true)?;
    socket2_socket.bind(&address)?;

    let socket = UdpSocket::from_std(socket2_socket.into())?;
    println!("Listening on [::]:1337");

    let mut buf = [0; 8192];
    loop {
        let (len, addr) = socket.recv_from(&mut buf).await?;
        //println!("{:?} bytes received from {:?}", len, addr);

        let len = socket.send_to(&buf[..len], addr).await?;
        //println!("{:?} bytes sent", len);
    }
}

#[tokio::main]
async fn main() -> io::Result<()> {
    let mut handles = vec![];
    for _ in 0..8 {
        println!("starting a process");
        handles.push(tokio::spawn(async move {
            // Process each socket concurrently.
            let result = process().await;
            println!("{:?}", result);
        }));
    }
    futures::future::join_all(handles).await;

    Ok(())
}

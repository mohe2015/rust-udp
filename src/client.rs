use tokio::net::UdpSocket;
use std::io;

#[tokio::main]
async fn main() -> io::Result<()> {
    let socket = UdpSocket::bind("[::]:1337").await?;
    println!("Listening on [::]:1337");

    socket.connect("192.168.2.121:1337").await?;
    let mut buf = [0; 1024];
    loop {
        let (len, addr) = socket.recv_from(&mut buf).await?;
        println!("{:?} bytes received from {:?}", len, addr);

        let len = socket.send_to(&buf[..len], addr).await?;
        println!("{:?} bytes sent", len);
    }

    Ok(())
}

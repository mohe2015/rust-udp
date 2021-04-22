use tokio::net::UdpSocket;
use std::io;

#[tokio::main]
async fn main() -> io::Result<()> {
    let socket = UdpSocket::bind("[::]:1337").await?;
    println!("Listening on [::]:1337");

    let mut buf = [0; 8192];
    loop {
        let (len, addr) = socket.recv_from(&mut buf).await?;
        //println!("{:?} bytes received from {:?}", len, addr);

        let len = socket.send_to(&buf[..len], addr).await?;
        //println!("{:?} bytes sent", len);
    }

    Ok(())
}

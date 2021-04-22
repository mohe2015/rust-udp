use tokio::net::UdpSocket;
use std::io;

#[tokio::main]
async fn main() -> io::Result<()> {
    let socket = UdpSocket::bind("[::]:1337").await?;
    println!("Listening on [::]:1337");

    let addr = "[2003:c0:470d:e2c8:8a3:837b:5f1b:73d9]:1337";
    socket.connect(addr).await?;
    let mut buf = [0; 1024];
    loop {
        let len = socket.send_to(&buf, addr).await?;
        //println!("{:?} bytes sent", len);

        let (len, addr) = socket.recv_from(&mut buf).await?;
        //println!("{:?} bytes received from {:?}", len, addr);
    }

    Ok(())
}

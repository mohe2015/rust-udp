use tokio::net::UdpSocket;
use std::io;
use std::net::{SocketAddr};

async fn process() -> io::Result<()> {
    let socket = UdpSocket::bind("[::]:0").await?;
    println!("Listening on [::]:1338");

    //let addr = "[2003:c0:470d:e2c8:8a3:837b:5f1b:73d9]:1337".parse::<SocketAddr>().unwrap();
    let addr = "[2003:c0:470d:e2c8:78a4:681c:1c74:3a7a]:1337".parse::<SocketAddr>().unwrap();
    socket.connect(addr).await?;
    let mut buf = [0; 8192];
    loop {
        let len = socket.send_to(&buf, addr).await?;
        //println!("{:?} bytes sent", len);

        let (len, addr) = socket.recv_from(&mut buf).await?;
        //println!("{:?} bytes received from {:?}", len, addr);
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
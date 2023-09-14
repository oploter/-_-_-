public class ChecksumString{
    public static void main(String[] args){
        byte[] bytes = args[0].getBytes();
        byte checksum = 0;
        byte k = (byte)211;
        for(byte b : bytes){
            checksum += b * k;
        }
        System.out.println((int)checksum + 128);
    }
}

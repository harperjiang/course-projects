package tools.elgamal;

public interface Cipher {

	public int ENCRYPT_MODE = 0;

	public int DECRYPT_MODE = 1;

	public void init(int type, Object key);

	public void update(byte[] data);

	public byte[] doFinal();
}

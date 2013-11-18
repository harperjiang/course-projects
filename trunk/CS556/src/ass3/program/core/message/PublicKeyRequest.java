package ass3.program.core.message;

public class PublicKeyRequest {

	private int bitLength;

	public PublicKeyRequest(int bitLength) {
		super();
		this.bitLength = bitLength;
	}

	public int getBitLength() {
		return bitLength;
	}

}

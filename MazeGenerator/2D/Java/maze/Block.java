package maze;

/**
 * 迷路画面で使うブロックのコンポーネントの基本的な形を決めるクラスです<br>
 * 壁、通路、スタートなどはこのクラスを継承したクラスのインスタンスです
 * @author naohS
 *
 */
public class Block {
	
	private BlockType blockType;
	
	/**
	 * enum型のBlockTypeクラスを用いてブロックの種類を初期化します
	 */
	public Block() {
		this.setBlockType(BlockType.PATH);
	}
	
	/**
	 * ブロックの種類を変更します
	 * @param blockType 変更するブロックタイプ
	 */
	public void setBlockType(BlockType blockType) {
		this.blockType = blockType;
	}
	
	/**
	 * 現在のブロックタイプを返します
	 * @return 現在のブロックタイプ
	 */
	public BlockType getBlockType() {
		return this.blockType;
	}
}

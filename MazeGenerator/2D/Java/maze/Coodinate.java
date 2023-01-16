package maze;

/**
 * coodinate
 * @author naohS
 *
 */
public class Coodinate {
	private int x;
	private int y;
	
	/**
	 * @param x x座標
	 * @param y y座標
	 */
	public Coodinate(int x, int y) {
		setX(x); setY(y);
	}
	
	/**
	 * Coodinate型の引数を受け取り座標を合わせます
	 * @param coodinate 変更する座標を持つ変数
	 */
	public void setXY(Coodinate coodinate) {this.x = coodinate.getX(); this.y = coodinate.getY();}
	/**
	 * xのセッター
	 * @param x セットするx座標
	 */
	public void setX(int x) {this.x = x;}
	/**
	 * yのセッター
	 * @param y セットするy座標
	 */
	public void setY(int y) {this.y = y;}
	/**
	 * x座標を返すメソッド
	 * @return x座標
	 */
	public int getX() {return this.x;}
	/**
	 * y座標を返すメソッド
	 * @return y座標
	 */
	public int getY() {return this.y;}
	/**
	 * equalsメソッドの定義です<br>
	 * containsメソッドなどで利用されます
	 */
	public boolean equals(Object coodinate) {return this.x == ((Coodinate)coodinate).x && this.y == ((Coodinate)coodinate).y;}
	/**
	 * toStringメソッドの定義です<br>
	 * 主にデバッグに使われます
	 */
	public String toString() {return "("+this.x+", "+this.y+") ";}
}

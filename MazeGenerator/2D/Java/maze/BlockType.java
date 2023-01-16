package maze;

/**
 * brock type
 * @author naohS
 *
 */
public enum BlockType {
	/**
	 * スタート
	 */
	START, 
	/**
	 * ゴール
	 */
	GOAL,
	/**
	 * 壁
	 */
	WALL,
	/**
	 * 通路
	 */
	PATH,
	/**
	 * 最短経路上にある
	 */
	SHORTEST_PATH
}

using UnityEngine;
using System.Collections.Generic;

public class Board : MonoBehaviour {

	public bool _____BoardPublic;

	// Width and Height
	public int size;
	public GameObject prefabSquare;
	public float spaceBetweenSquares;
	public bool moving;
	public bool moveTime;

	public bool _____BoardPrivate;

	public GameObject[,] squareGOs;
	public GameObject[,] originalBoard;

	// Use this for initialization
	void Start() {
		createBoard();
		initSquarePositions();
	}

	private void createBoard() {
		squareGOs = new GameObject[size, size];
		int number = 0;
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				squareGOs[i, j] = Instantiate(prefabSquare);
				Square square = squareGOs[i, j].GetComponent<Square>();
				square.number = number++;
			}
		}
	}

	private void initSquarePositions() {
		float squareWidth = prefabSquare.GetComponent<Renderer>().bounds.size.x;
		float boardWidth = (size * squareWidth) + ((size - 1) * spaceBetweenSquares);
		float left = (-boardWidth / 2) + (squareWidth / 2);
		float top = -left;
		float step = squareWidth + spaceBetweenSquares;
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				GameObject squareGO = squareGOs[i, j];
				Vector3 position = Vector3.zero;
				position.z = top - (step * i);
				position.x = left + (step * j);
				squareGO.transform.position = position;
			}
		}
	}

	// Update is called once per frame
	void Update() {
		
	}

	public void slideColumn(int columnNumber, int slideAmount = 1, bool trackSlide = true) {

	}

	public void slideRow(int rowNumber, int slideAmount = 1, bool trackSlide = true) {

	}

	public void restoreOriginal() {

	}

	public void undo() {

	}
}

package com.example.ky;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.view.View;

public class KyView extends View {

    private Paint gridPaint;
    private Paint outlinePaint;
    private Rect gridRect;
    private float gridMargin = 50; // Adjust margin as needed
    public KyView(Context context) {
        super(context);
        init();
    }

    private void init() {
        gridPaint = new Paint();
        gridPaint.setColor(Color.RED);
        gridPaint.setStrokeWidth(2); // Adjust stroke width as needed

        outlinePaint = new Paint();
        outlinePaint.setColor(Color.WHITE);
        outlinePaint.setStrokeWidth(4); // Adjust outline width as needed

        gridRect = new Rect();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        int cellSize;

        int width = getWidth();
        int height = getHeight();


        // Calculate drawing area with margins
        int drawingWidth = width - (int) (gridMargin * 2);
        int drawingHeight = height - (int) (gridMargin * 2);

        // Set grid rectangle dimensions
        gridRect.left = (int) gridMargin;
        gridRect.top = (int) gridMargin;

        if (width>height){
            gridRect.right = gridRect.left + drawingHeight;
            gridRect.bottom = gridRect.top + drawingWidth;
            cellSize = drawingHeight / 5;
        } else {
            gridRect.right = gridRect.left + drawingWidth;
            gridRect.bottom = gridRect.top + drawingHeight;

            // Calculate cell size
            cellSize = drawingWidth / 5;
        }

        // Draw outline
        canvas.drawRect(gridRect, outlinePaint);

        // Calculate cell size

        // Draw horizontal lines
        for (int i = 0; i < 6; i++) {
            int y = gridRect.top + (i * cellSize);
            canvas.drawLine(gridRect.left, y, gridRect.right, y, gridPaint);
        }

        // Draw vertical lines
        for (int i = 0; i < 6; i++) {
            int x = gridRect.left + (i * cellSize);
            canvas.drawLine(x, gridRect.top, x, gridRect.top+cellSize*5, gridPaint);
        }
    }
}
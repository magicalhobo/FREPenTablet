package
{
	import com.magicalhobo.utils.PenTablet;
	
	import flash.display.Sprite;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.text.TextField;
	
	[SWF(frameRate="60")]
	
	public class PenTabletDemo extends Sprite
	{
		private var output:TextField;
		private var tablet:PenTablet;
		
		public function PenTabletDemo()
		{
			stage.scaleMode = StageScaleMode.NO_SCALE;
			stage.align = StageAlign.TOP_LEFT;
			
			output = new TextField();
			output.width = stage.stageWidth;
			output.height = stage.stageHeight;
			output.mouseEnabled = false;
			
			tablet = new PenTablet();
			log('Context: '+PenTablet.context);
			
			stage.addEventListener(MouseEvent.MOUSE_DOWN, mouseDownHandler);
			stage.addEventListener(MouseEvent.MOUSE_UP, mouseUpHandler);
			
			addChild(output);
		}
		
		protected function mouseDownHandler(ev:MouseEvent):void
		{
			graphics.moveTo(mouseX, mouseY);
			stage.addEventListener(MouseEvent.MOUSE_MOVE, mouseMoveHandler);
		}
		
		protected function mouseMoveHandler(ev:MouseEvent):void
		{
			var pressure:uint = 512;
			try
			{
				pressure = tablet.getPressure();
				log('Pressure: '+pressure);
			}
			catch(e:*)
			{
				log('Error: '+e);
			}
			graphics.lineStyle(pressure/50);
			graphics.lineTo(mouseX, mouseY);
		}
		
		protected function mouseUpHandler(ev:MouseEvent):void
		{
			stage.removeEventListener(MouseEvent.MOUSE_MOVE, mouseMoveHandler);
		}
		
		private function log(message:String):void
		{
			output.text = message + '\n' + output.text;
		}
	}
}
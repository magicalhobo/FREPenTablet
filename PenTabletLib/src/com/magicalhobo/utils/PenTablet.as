package com.magicalhobo.utils
{
	import flash.external.ExtensionContext;

	public class PenTablet
	{
		public static const VERSION:Number = 1.0;
		
		public static var context:ExtensionContext;
		
		public function PenTablet()
		{
			if(!context)
			{
				context = ExtensionContext.createExtensionContext('com.magicalhobo.utils.PenTablet', '');
			}
		}
		
		public function getPressure():uint
		{
			var pressure:uint = context.call('getPressure') as uint;
			return pressure;
		}
	}
}
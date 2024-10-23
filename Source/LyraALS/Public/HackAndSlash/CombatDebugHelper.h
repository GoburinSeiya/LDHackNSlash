#pragma once

namespace Debug
{
	static void Print(const FString& Message, const FColor& Color = FColor::MakeRandomColor(), int32 intKey = -1)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 7.f, Color, Message);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}
}
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

	static void Print(const FString& FloatTitle, float FloatValue, int32 InKey = -1, const FColor& Color = FColor::MakeRandomColor())
	{
		if(GEngine)
		{
			const FString FinalMessage = FloatTitle + TEXT(": ") + FString::SanitizeFloat(FloatValue);
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, FinalMessage);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMessage);
		}
	}
}
function Main()
  while IsScreenOpened()
    Cls(RGB(0, 0, 64))
    SetColor(RGB(255, 128, 0))
    DrawRect(300, 300, 100, 100)
    RefreshScreen()
  end
end

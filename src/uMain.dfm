object hGame: ThGame
  Left = 0
  Top = 0
  HorzScrollBar.Smooth = True
  HorzScrollBar.ThumbSize = 20
  HorzScrollBar.Tracking = True
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  ClientHeight = 310
  ClientWidth = 645
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnMouseDown = FormMouseDown
  OnMouseWheel = FormMouseWheel
  PixelsPerInch = 96
  TextHeight = 13
  object GameLoop: TTimer
    Enabled = False
    Interval = 80
    OnTimer = GameLoopTimer
    Left = 584
    Top = 72
  end
  object PopupMenu: TPopupMenu
    Left = 584
    Top = 16
    object AdicionarObjecto1: TMenuItem
      Caption = 'Adicionar'
      object Pokemon1: TMenuItem
        Caption = 'Pokemon'
        object N11: TMenuItem
          Caption = '1'
          OnClick = N11Click
        end
        object N21: TMenuItem
          Caption = '2'
          OnClick = N21Click
        end
        object N31: TMenuItem
          Caption = '3'
          OnClick = N31Click
        end
        object N41: TMenuItem
          Caption = '4'
          OnClick = N41Click
        end
        object N51: TMenuItem
          Caption = '5'
          OnClick = N51Click
        end
        object N61: TMenuItem
          Caption = '6'
          OnClick = N61Click
        end
        object N71: TMenuItem
          Caption = '7'
          OnClick = N71Click
        end
        object N81: TMenuItem
          Caption = '8'
          OnClick = N81Click
        end
        object N91: TMenuItem
          Caption = '9'
          OnClick = N91Click
        end
        object N101: TMenuItem
          Caption = '10'
          OnClick = N101Click
        end
      end
      object rvore1: TMenuItem
        Caption = #193'rvore'
        object N12: TMenuItem
          Caption = '1'
          OnClick = N12Click
        end
        object N22: TMenuItem
          Caption = '2'
          OnClick = N22Click
        end
        object N32: TMenuItem
          Caption = '3'
          OnClick = N32Click
        end
        object N42: TMenuItem
          Caption = '4'
          OnClick = N42Click
        end
      end
      object Rocha1: TMenuItem
        Caption = 'Rocha'
        object N13: TMenuItem
          Caption = '1'
          OnClick = N13Click
        end
        object N23: TMenuItem
          Caption = '2'
          OnClick = N23Click
        end
      end
      object Placa1: TMenuItem
        Caption = 'Placa'
        OnClick = Placa1Click
      end
      object Bloco1: TMenuItem
        Caption = 'Bloco'
        OnClick = Bloco1Click
      end
    end
    object RemoverObjeto1: TMenuItem
      Caption = 'Remover'
      OnClick = RemoverObjeto1Click
    end
    object ModoDesenho1: TMenuItem
      Caption = 'Modo Desenho'
      OnClick = ModoDesenho1Click
    end
    object ModoApagar1: TMenuItem
      Caption = 'Modo Apagar'
      OnClick = ModoApagar1Click
    end
    object LimparMapa1: TMenuItem
      Caption = 'Limpar Mapa'
      OnClick = LimparMapa1Click
    end
    object PararMusicadefundo1: TMenuItem
      Caption = 'Parar Musica de fundo'
      OnClick = PararMusicadefundo1Click
    end
  end
  object GameWalk: TTimer
    Enabled = False
    OnTimer = GameWalkTimer
    Left = 584
    Top = 128
  end
  object GamePad: TTimer
    Interval = 80
    OnTimer = GamePadTimer
    Left = 584
    Top = 192
  end
end

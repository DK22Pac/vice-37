case CREATE_PLAYER:
	// Получаем в стек (читай, буфер) параметров 4 параметра
    CRunningScript::CollectParameters(this, 4);
	// this - это обьект (класс) CRunningScript, который описывает скрипт, его состояние.

	// Запишем значения параметров в переменные, чтобы было "легче" к ним обращаться
    unsigned int playedId = ScriptParams[0];
	float x = ScriptParams[1];
	float y = ScriptParams[2];
	float z = ScriptParams[3];
	// ScriptParams - это массив параметров. Буфер, который используем для обмена параметрами.
	// Несложно догадаться, что в этом массиве - 32 элемента. Столько, сколько и локальных
	// переменных в скрипте.

	// Проверяем, загружена ли модель в слоте 0. Член ms_aInfoForModel - массив структур, которые описывают
	// состояние моделей. Размер этого массива - 26316 элементов (таким образом, здесь хранится информация о
	// состоянии загруженности всех обьектов (моделей) игры).
    if ( CStreaming::ms_aInfoForModel[0].bLoadState != 1 )
	// Если модель не загружена, загружаем её.
    {
		// Загружаем модель "player" в слот 0
		CStreaming::RequestSpecialModel(0, "player", 0x1A);
		// Да, именно эта функция вызывается из опкода 038B.
		CStreaming::LoadAllRequestedModels(1);
    }
	// Установки для педа-игрока. Функция рассмотрена ниже.
    CPlayerPed::SetupPlayerPed(playedId);
	// В переменную player записываем обьект (класс) игрока с индексом playedId. Массив Players содержит 2 элемента
	// (2 игрока)
    CPlayer *player = &CWorld::Players[playedId];
	// Какая-то функция для педа-игрока... Устанавливается DecisionMaker и аккуратность melee-атак в 30.0
    sub_5E47E0(CWorld::Players[playedId].m_pPed, 2);
	// Удаляем педа из игрового мира (удаляются все ссылки к этому педу)
    CPlayerPed::DeactivatePlayerPed((CEntity *)playedId);
	// Если полученная z-кордината меньше от (-100), находим z-координату поверхности (земли) по координатам (x,y)
    if(z <= -100.0)
        z = CWorld::FindGroundZForCoord(x, y);
	// Добавляем к переменной z расстояние от земли к центру педа
    z += CEntity::GetDistanceFromCentreOfMassToBaseOfModel(player->m_pPed);
	// Теперь устанавливаем педу позицию в (x,y,z). Заметьте, что это ещё не физическое "перемещение" педа. Ведь мы
	// удалили его из мира.
    CPlaceable::SetPos(player->m_pPed, x, y, z);
	// Скопируем координаты в структуру CVector (нужно для следуещей функции)
	CVector pos;
    pos.x = x;
    pos.y = y;
    pos.z = z;
	// Убираем всё лишнее для "посадки" :) педа
    CTheScripts::ClearSpaceForMissionEntity(&pos, player->ped);
	// А вот теперь добавляем педа в игроой мир.
    CPlayerPed::ReactivatePlayerPed(playedId);
	// Важный момент. Опкод возвращает хендл новосозданного игрока. Как видим, этот тот же номер, который мы
	// передали в опкод в виде параметра. Т.е., хендл игрока - это его номер в массиве игроков (т.е. либо 0, либо 1,
	// обычно в игре задеяе только один игрок).
    ScriptParams[0] = playedId;
	// Передаем параметр "обратно" в скрипт (поток)
    CRunningScript::StoreParameters(1);
	// Эту часть не стал подробно разбирать. Здесь устанавливаются задачи игроку (task'и). Ставится группа анимации
	// "playidles".
    allocated = CTask::operator new(28);
    if (allocated)
        CTaskSimpleProcessPlayerWeapon *task = CTaskSimpleProcessPlayerWeapon::CTaskSimpleProcessPlayerWeapon(allocated);
    else
        task = 0;
    CPedIntelligence *intelligence = player->m_pPed->intelligence;
    CPedTasks::AssignPrimaryTask(&intelligence->m_pedTasks, task, 4, 0);
    return 0;

Функция CPlayerPed::SetupPlayerPed(unsigned int playedId). В этой функции создается пед для игрока.

void CPlayerPed::SetupPlayerPed(int playerId)
{
	// Выделяем место в пуле педов для нового педа.
    CPed *ped = PedPool::Allocate();
    if(ped)
		// Эта функция - конструктор. Она "строит" (да-да) педа, устанавливает для него базовые параметры
		ped = CPlayerPed::CPlayerPed(ped, playerId, 0);
    else
		ped = 0;
	// Прикрепляем педа к игроку с id playerId.
    CWorld::Players[playerId].m_pPed = ped;
	// Если игрок - не первый, а второй (не забываем, что индексация начинается с нуля), то ставим педу тип
	// PLAYER2.
    if(playerId == 1)
		ped->pedType = PLAYER2;
	// Устанавливаем вращение в 0.
    CPlaceable::setRotation(CWorld::Players[playerId].m_pPed, 0.0, 0.0, 0.0);
	// Помещаем педа в игровой мир.
    CWorld::Add((CEntity *)CWorld::Players[playerId].m_pPed);
	// Уровень меткости - на 100.
    CWorld::Players[playerId].m_pPed->weaponAccuracy = 100;
	// Устанавливаем флаг isWastedBusted в 0.
    CWorld::Players[playerId].isWastedBusted = 0;
}

